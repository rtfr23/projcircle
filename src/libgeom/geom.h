#pragma once
struct figura {
    int x;
    int y;
    float radius;
};
void arrowin(int id);
int zap_id(char* ptr);
int skob_id(char* ptr);
int skob_id2(char* ptr);
int prob_id1(char* ptr);
int prob_id2(char* ptr);
int rad_id(char* ptr, char* rad);
void radius(char* ptr, char* rad);
void sixcheck(char* ptr);
void namecheck(char* ptr, struct figura* circle, char* rad);
void xcheck(char* ptr);
void ycheck(char* ptr);
void radcheck(char* rad, char* ptr);
void probelcheck1(char* ptr);
void radminus(char* ptr, char* rad);
void unexpected_check(char* ptr);
void skobcheck(char* ptr, char* rad);
