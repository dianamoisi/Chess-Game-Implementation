#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sah.h"



int const direction_i[18] = {0,  0, -1, 1, -1, -1, 1,  1, -2, -2, 2,  2, 1, -1,  1, -1, 1, 2};
int const direction_j[18] = {1, -1,  0, 0,  1, -1, 1, -1,  1, -1, 1, -1, 2,  2, -2, -2, 0, 0};

void encode(char table[][8], char* fen) {
	int n = 0;
    int contor = 0;

    if(fen == NULL) {
        printf("%s : %d a fost o eroare de alocare de memorie", __FILE__, __LINE__);
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(table[i][j] != ' ') {
                n++;
                fen[n - 1] = table[i][j];
            } else {
                n++;
                contor = 0;
                while((table[i][j] == ' ') && (j < 8)) {
                    j++;
                    contor++;
                }
                j--;
                fen[n - 1] = contor + 48;
            }
        }
			if(i != 7) {
				n++;
                fen[n - 1] = '/';
			}
    }
}



bool it_is_rival(char x, char y) {
    if((65 <= x) && (x <= 90)){
            if((65 <= y) && (y <= 90)) {
                return false;
            } else {
            //inseamna ca piesa care va fi mutat este alba, si a intalnit o piesa de culoare neagra
                if(y != 'k') {
                    return true;
                } else {
                return false;
                }
            }
    } else {
            if((65 <= y) && (y <= 90)) {
            // piesa neagra a intalnit una alba, se vefifica daca nu este regele alb
                if(y != 'K') {
                    return true;
                } else {
                    return false;
                    }
            } else {
                return false;
            }
    }
}

bool is_the_other_color(char piece, char tomove) {
    if(tomove == 'w') {
        if(65 <= piece && piece <= 90) {
            return true;
        } else {
            return false;
        }
    }
    else {
        if(65 <= piece && piece <= 90) {
            return false;
        } else {
            return true;
        }
    }
}


void print(char table[][8]){
    printf("   ");
    for(int i = 0; i < 8; i++) {
        printf("%c ", i + 'a');
    }
    printf("\n\n");
    for(int i = 0; i < 8; i++) {
        printf("%d  ", 8 - i);
        for(int j = 0; j < 8; j++)
            printf("%c ",  table[i][j]);

	    printf("\n");
	}
}


int find_the_muves(char tabla[8][8], move* sir, int r, int c) {
    int contor = 0;
    char piece = tabla[r][c];
    switch(piece) {
        case ('p') :{
            int l1 = 0;
            if(r == 1) {
                l1 = 18;
            } else {
                l1 = 17;
            }
            for(int i = 16; i < l1; i++){
                if((r + direction_i[i] < 8) && (0 <= r + direction_i[i]) && (c + direction_j[i] < 8) && (0 <= c + direction_j[i])) {
                    if(tabla[r + direction_i[i]][c + direction_j[i]] == ' ') {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = c + direction_j[i];
                        sir[contor].r2 = r + direction_i[i];
                        contor++;
                    }
                }
            }
            for(int i = 6; i < 8; i++) {
                if((r + direction_i[i] < 8) && (0 <= r + direction_i[i]) && (c + direction_j[i] < 8) && (0 <= c + direction_j[i])) {
                    if(it_is_rival(piece, tabla[r + direction_i[i]][c + direction_j[i]])) {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = c + direction_j[i];
                        sir[contor].r2 = r + direction_i[i];
                        contor++;
                    }
                }
            }
            break;
        }
        case ('P'):{
            int l1 = 0;
            if(r == 6) {
                l1 = 18;
            } else {
                l1 = 17;
            }
            for(int i = 16; i < l1; i++){
                if((r - direction_i[i] < 8) && (0 <= r - direction_i[i]) && (c + direction_j[i] < 8) && (0 <= c + direction_j[i])){
                    if(tabla[r - direction_i[i]][c + direction_j[i]] == ' ') {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = c + direction_j[i];
                        sir[contor].r2 = r - direction_i[i];
                        contor++;
                    }
                }
            }
            for(int i = 4; i < 6; i++) {
                if((r + direction_i[i] < 8) && (0 <= r + direction_i[i]) && (c + direction_j[i] < 8) && (0 <= c + direction_j[i])) {
                    if(it_is_rival(piece, tabla[r + direction_i[i]][c + direction_j[i]])) {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = c + direction_j[i];
                        sir[contor].r2 = r + direction_i[i];
                        contor++;
                    }
                }
            }
            break;
        }
        case ('k'):
        case ('K'):
        case ('n'):
        case ('N'): {
            int l1, l2;
            if(piece == 'k' || piece == 'K') {
                l1 = 0;
                l2 = 8;
            }
            if(piece == 'n' || piece == 'N'){
                l1 = 8;
                l2 = 16;
            }
            for(int i = l1; i < l2; i++) {
                if((r + direction_i[i] < 8) && (0 <= r + direction_i[i]) && (c + direction_j[i] < 8) && (0 <= c + direction_j[i])) {
                    if(tabla[r + direction_i[i]][c + direction_j[i]] == ' ' || it_is_rival(piece, tabla[r + direction_i[i]][c + direction_j[i]])) {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = c + direction_j[i];
                        sir[contor].r2 = r + direction_i[i];
                        contor++;
                    }
                }
            }
            break;
        }
        case ('q'):
        case ('Q'):
        case ('b'):
        case ('B'):
        case ('r'):
        case ('R'):
        {
            int l1, l2;
            if((piece == 'q') || (piece == 'Q')) {
                l1 = 0;
                l2 = 8;
            }
            if((piece == 'b') || (piece == 'B')){
                l1 = 4;
                l2 = 8;
            }
            if((piece == 'r') || (piece == 'R')) {
                l1 = 0;
                l2 = 4;
            }
            for(int i = l1; i < l2; i++) {
                int aux_r = r;
                int aux_c = c;
                while((aux_r + direction_i[i] < 8) && (0 <= aux_r + direction_i[i]) && (aux_c + direction_j[i] < 8) && (0 <= aux_c + direction_j[i])) {
                    if(tabla[aux_r + direction_i[i]][aux_c + direction_j[i]] == ' ' || it_is_rival(piece, tabla[aux_r + direction_i[i]][aux_c + direction_j[i]])) {
                        sir[contor].c1 = c;
                        sir[contor].r1 = r;
                        sir[contor].c2 = aux_c + direction_j[i];
                        sir[contor].r2 = aux_r + direction_i[i];
                        contor++;
                        aux_c = aux_c + direction_j[i];
                        aux_r = aux_r + direction_i[i];
                        if(tabla[aux_r][aux_c] != ' '){
                            break;
                        }
                    } else{
                        break;
                    }
                }
            }

        }
    }
    return contor;
}

void find_piece(char table[][8], char piece, int* col, int* row) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(table[i][j] == piece) {
                *col = j;
                *row = i;
            }
        }
    }
}



int all_moves(char table[][8], char tomove, move* sir) {
    // move sir[140];
    int contor = 0;
    move aux[30];
    int contaux = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            contaux = 0;
            if(is_the_other_color(table[i][j], tomove)){
                contaux = find_the_muves(table, aux, i, j);
                for(int k = 0; k < contaux; k++) {
                    sir[contor].r1 = aux[k].r1;
                    sir[contor].c1 = aux[k].c1;
                    sir[contor].r2 = aux[k].r2;
                    sir[contor].c2 = aux[k].c2;
                    contor++;
                }
            }
        }
    }
    sir[contor].c1 = 0;
    sir[contor].c2 = 0;
    sir[contor].r1 = 0;
    sir[contor].r2 = 0;
    return contor;
}





int it_is_ok(config t) {
    //voi reface tema de data trecuta
    //verificam daca regele este in sah mat
    char tomove;
    int c1, c2, r1, r2;
    c1 = t.mv.c1 - 97;
    c2 = t.mv.c2 - 97;
    r1 = 8 - t.mv.r1;
    r2 = 8 - t.mv.r2;
    char piece = t.table[c1][r1]; // asta este piesa pe care dorim sa o mutam
    //eu voi pune tomove setat pe culoarea care a mutat inainte pt a verifica daca regele este in sah sau nu
    if((65 <= piece) && (piece <= 90)) {
        tomove = 'b';
    } else{
        tomove = 'w';
    }

    move sir[170]; //stocam mutarile in variabila aceasta
    int contor = all_moves(t.table, tomove, sir);
    int cr, rr;

    //daca albul muta, trebuie verificat daca negrul da sau nu sah mat
    if(tomove == 'w') {
        find_piece(t.table, 'k', &cr, &rr);
    } else {
        find_piece(t.table, 'K', &cr, &rr);
    }

    for(int i = 0; i < contor; i++) {
        if((sir[i].c2 == cr) && (sir[i].r2 == rr)){
            return 0; //regele este in sah
        }
    }

    //se verifica daca piesa doreste sa faca mutarea buna
    bool stare = false;
    contor = find_the_muves(t.table, sir, r1, c1);
    for(int i = 0; i < contor; i++) {
        if((sir[i].r2 == r2) && (sir[i].c2 == c2)){
            stare = true;
        }
    }
    if(stare) {
        return 1;
    } else {
        return 0;
    }

}


void run_tests(){
    FILE *fin = NULL;
	int n = 0;
	config conf[500];

	fin = fopen("chess_in.bin", "rb");
	if(fin == NULL) {
		perror("ERROR at reading file");
		exit(-1);
	}

	fread(&n, sizeof(int), 1, fin);

	for(int i = 0; i < n; i++) {
		fread(&conf[i], sizeof(conf), 1, fin);
	}
    fclose(fin);
    FILE *fout = NULL;
    fout = fopen("chess_answers.txt", "w");

    if(fout == NULL) {
        perror("ERROR at making new file");
        exit(-2);
    }
	for(int i = 0; i < n; i++) {
        int ok = it_is_ok(conf[i]);
        fprintf(fin, "%d\n", ok);
	}
    fclose(fout);


}
